using UnityEngine;

namespace NewSimulator.Player
{
    /// <summary>
    /// First-person inspection camera with an optional free-flight mode.
    /// Uses Unity's legacy Input API so the first milestone has no extra package dependency.
    /// </summary>
    [DisallowMultipleComponent]
    public sealed class FreeFlyCameraController : MonoBehaviour
    {
        [Header("Movement")]
        [SerializeField, Min(0.1f)] private float walkSpeed = 6f;
        [SerializeField, Min(1f)] private float sprintMultiplier = 2.5f;
        [SerializeField, Min(0.1f)] private float acceleration = 18f;

        [Header("Look")]
        [SerializeField, Min(0.01f)] private float mouseSensitivity = 2f;
        [SerializeField, Range(1f, 89f)] private float verticalLookLimit = 85f;

        [Header("Modes")]
        [SerializeField] private bool freeFlight = true;
        [SerializeField] private KeyCode toggleFreeFlightKey = KeyCode.F;

        private Vector3 velocity;
        private float pitch;
        private bool cursorCaptured;

        private void OnEnable()
        {
            Vector3 euler = transform.eulerAngles;
            pitch = NormalizeAngle(euler.x);
            CaptureCursor(true);
        }

        private void OnDisable()
        {
            CaptureCursor(false);
        }

        private void Update()
        {
            if (Input.GetKeyDown(KeyCode.Escape)) CaptureCursor(false);
            if (Input.GetMouseButtonDown(0)) CaptureCursor(true);
            if (Input.GetKeyDown(toggleFreeFlightKey)) freeFlight = !freeFlight;

            if (cursorCaptured) UpdateLook();
            UpdateMovement();
        }

        private void UpdateLook()
        {
            float yaw = Input.GetAxisRaw("Mouse X") * mouseSensitivity;
            float pitchDelta = Input.GetAxisRaw("Mouse Y") * mouseSensitivity;

            pitch = Mathf.Clamp(pitch - pitchDelta, -verticalLookLimit, verticalLookLimit);
            transform.localRotation = Quaternion.Euler(pitch, transform.eulerAngles.y + yaw, 0f);
        }

        private void UpdateMovement()
        {
            Vector3 input = new Vector3(Input.GetAxisRaw("Horizontal"), 0f, Input.GetAxisRaw("Vertical"));
            input = Vector3.ClampMagnitude(input, 1f);

            Vector3 desiredDirection = transform.right * input.x + transform.forward * input.z;

            if (freeFlight)
            {
                float vertical = 0f;
                if (Input.GetKey(KeyCode.E)) vertical += 1f;
                if (Input.GetKey(KeyCode.Q)) vertical -= 1f;
                desiredDirection += Vector3.up * vertical;
            }
            else
            {
                desiredDirection.y = 0f;
                desiredDirection = desiredDirection.sqrMagnitude > 0f ? desiredDirection.normalized : Vector3.zero;
            }

            float speed = walkSpeed * (Input.GetKey(KeyCode.LeftShift) ? sprintMultiplier : 1f);
            Vector3 targetVelocity = desiredDirection.normalized * speed;
            velocity = Vector3.MoveTowards(velocity, targetVelocity, acceleration * Time.unscaledDeltaTime);
            transform.position += velocity * Time.unscaledDeltaTime;
        }

        private void CaptureCursor(bool capture)
        {
            cursorCaptured = capture;
            Cursor.lockState = capture ? CursorLockMode.Locked : CursorLockMode.None;
            Cursor.visible = !capture;
        }

        private static float NormalizeAngle(float angle)
        {
            if (angle > 180f) angle -= 360f;
            return angle;
        }
    }
}
