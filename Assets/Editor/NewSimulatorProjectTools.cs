using System.IO;
using NewSimulator.Player;
using NewSimulator.World;
using UnityEditor;
using UnityEditor.SceneManagement;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.SceneManagement;

namespace NewSimulator.Editor
{
    public static class NewSimulatorProjectTools
    {
        private const string SettingsFolder = "Assets/Settings";
        private const string SettingsPath = SettingsFolder + "/ProceduralCitySettings.asset";
        private const string SceneFolder = "Assets/Scenes";
        private const string ScenePath = SceneFolder + "/Version01Demo.unity";

        [MenuItem("New Simulator/Generate Version 0.1 Demo Scene")]
        public static void GenerateVersion01DemoScene()
        {
            EnsureFolder(SettingsFolder);
            EnsureFolder(SceneFolder);

            ProceduralCitySettings settings = AssetDatabase.LoadAssetAtPath<ProceduralCitySettings>(SettingsPath);
            if (settings == null)
            {
                settings = ScriptableObject.CreateInstance<ProceduralCitySettings>();
                AssetDatabase.CreateAsset(settings, SettingsPath);
            }

            Scene scene = EditorSceneManager.NewScene(NewSceneSetup.EmptyScene, NewSceneMode.Single);
            scene.name = "Version01Demo";

            CreateCamera();
            CreateSun();
            CreateCity(settings);
            CreateGlobalVolumePlaceholder();

            EditorSceneManager.SaveScene(scene, ScenePath);
            AssetDatabase.SaveAssets();
            AssetDatabase.Refresh();
            Selection.activeObject = AssetDatabase.LoadAssetAtPath<SceneAsset>(ScenePath);

            Debug.Log($"New Simulator Version 0.1 demo generated at {ScenePath}.");
        }

        [MenuItem("New Simulator/Validate Project Setup")]
        public static void ValidateProjectSetup()
        {
            int errors = 0;
            int warnings = 0;

            RenderPipelineAsset pipeline = GraphicsSettings.currentRenderPipeline;
            if (pipeline == null)
            {
                Debug.LogError("No Scriptable Render Pipeline asset is active. This project is intended to use HDRP.");
                errors++;
            }
            else if (!pipeline.GetType().Name.Contains("HDRenderPipeline"))
            {
                Debug.LogWarning($"Active render pipeline is {pipeline.GetType().Name}, not HDRP.");
                warnings++;
            }

            if (AssetDatabase.LoadAssetAtPath<ProceduralCitySettings>(SettingsPath) == null)
            {
                Debug.LogWarning("Procedural city settings do not exist yet. Run Generate Version 0.1 Demo Scene.");
                warnings++;
            }

            if (!File.Exists(ScenePath))
            {
                Debug.LogWarning("Version 0.1 demo scene has not been generated yet.");
                warnings++;
            }

            string colorSpace = PlayerSettings.colorSpace.ToString();
            if (PlayerSettings.colorSpace != ColorSpace.Linear)
            {
                Debug.LogWarning($"Color space is {colorSpace}. Photorealistic HDRP projects should use Linear color space.");
                warnings++;
            }

            Debug.Log($"New Simulator validation complete. Errors: {errors}, warnings: {warnings}.");
        }

        private static void CreateCamera()
        {
            GameObject cameraObject = new GameObject("Player Camera");
            cameraObject.transform.position = new Vector3(0f, 2.2f, -45f);
            cameraObject.transform.rotation = Quaternion.Euler(8f, 0f, 0f);
            Camera camera = cameraObject.AddComponent<Camera>();
            camera.nearClipPlane = 0.05f;
            camera.farClipPlane = 5000f;
            cameraObject.AddComponent<AudioListener>();
            cameraObject.AddComponent<FreeFlyCameraController>();
        }

        private static void CreateSun()
        {
            GameObject sunObject = new GameObject("Sun");
            sunObject.transform.rotation = Quaternion.Euler(42f, -32f, 0f);
            Light light = sunObject.AddComponent<Light>();
            light.type = LightType.Directional;
            light.intensity = 3.14f;
            light.shadows = LightShadows.Soft;
        }

        private static void CreateCity(ProceduralCitySettings settings)
        {
            GameObject cityObject = new GameObject("Generated City");
            ProceduralCityGenerator generator = cityObject.AddComponent<ProceduralCityGenerator>();
            generator.Settings = settings;
            generator.Generate();
        }

        private static void CreateGlobalVolumePlaceholder()
        {
            GameObject volumeObject = new GameObject("Global Volume");
            Volume volume = volumeObject.AddComponent<Volume>();
            volume.isGlobal = true;
            volume.priority = 0f;
        }

        private static void EnsureFolder(string path)
        {
            if (AssetDatabase.IsValidFolder(path)) return;

            string parent = Path.GetDirectoryName(path)?.Replace('\\', '/');
            string name = Path.GetFileName(path);
            if (string.IsNullOrEmpty(parent) || string.IsNullOrEmpty(name)) return;

            if (!AssetDatabase.IsValidFolder(parent)) EnsureFolder(parent);
            AssetDatabase.CreateFolder(parent, name);
        }
    }
}
