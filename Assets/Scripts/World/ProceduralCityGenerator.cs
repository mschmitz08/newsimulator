using UnityEngine;

namespace NewSimulator.World
{
    /// <summary>
    /// Deterministic Version 0.1 city massing generator. The generated geometry is intentionally simple,
    /// but its layout and configuration model are designed to be replaced incrementally by higher-detail systems.
    /// </summary>
    [DisallowMultipleComponent]
    public sealed class ProceduralCityGenerator : MonoBehaviour
    {
        [SerializeField] private ProceduralCitySettings settings;
        [SerializeField] private Material groundMaterial;
        [SerializeField] private Material roadMaterial;
        [SerializeField] private Material sidewalkMaterial;
        [SerializeField] private Material[] buildingMaterials;

        public ProceduralCitySettings Settings
        {
            get => settings;
            set => settings = value;
        }

        [ContextMenu("Generate City")]
        public void Generate()
        {
            if (settings == null)
            {
                Debug.LogError("ProceduralCityGenerator requires ProceduralCitySettings.", this);
                return;
            }

            ClearGeneratedChildren();
            Random.State previousState = Random.state;
            Random.InitState(settings.randomSeed);

            try
            {
                GenerateGround();
                GenerateRoadGrid();
                GenerateBlocks();
            }
            finally
            {
                Random.state = previousState;
            }
        }

        [ContextMenu("Clear Generated City")]
        public void ClearGeneratedChildren()
        {
            for (int i = transform.childCount - 1; i >= 0; i--)
            {
                GameObject child = transform.GetChild(i).gameObject;
#if UNITY_EDITOR
                if (!Application.isPlaying) DestroyImmediate(child);
                else Destroy(child);
#else
                Destroy(child);
#endif
            }
        }

        private void GenerateGround()
        {
            float width = settings.blocksX * settings.CellSize + settings.roadWidth;
            float depth = settings.blocksZ * settings.CellSize + settings.roadWidth;
            GameObject ground = CreateBox("Ground", new Vector3(0f, -0.5f, 0f), new Vector3(width, 1f, depth), groundMaterial);
            ground.transform.SetParent(transform, true);
        }

        private void GenerateRoadGrid()
        {
            float totalX = settings.blocksX * settings.CellSize + settings.roadWidth;
            float totalZ = settings.blocksZ * settings.CellSize + settings.roadWidth;
            float startX = -totalX * 0.5f;
            float startZ = -totalZ * 0.5f;

            for (int x = 0; x <= settings.blocksX; x++)
            {
                float roadX = startX + settings.roadWidth * 0.5f + x * settings.CellSize;
                CreateBox("Road_NS", new Vector3(roadX, 0.01f, 0f), new Vector3(settings.roadWidth, 0.02f, totalZ), roadMaterial).transform.SetParent(transform, true);
            }

            for (int z = 0; z <= settings.blocksZ; z++)
            {
                float roadZ = startZ + settings.roadWidth * 0.5f + z * settings.CellSize;
                CreateBox("Road_EW", new Vector3(0f, 0.02f, roadZ), new Vector3(totalX, 0.02f, settings.roadWidth), roadMaterial).transform.SetParent(transform, true);
            }
        }

        private void GenerateBlocks()
        {
            float totalX = settings.blocksX * settings.CellSize + settings.roadWidth;
            float totalZ = settings.blocksZ * settings.CellSize + settings.roadWidth;
            float originX = -totalX * 0.5f + settings.roadWidth + settings.blockSize * 0.5f;
            float originZ = -totalZ * 0.5f + settings.roadWidth + settings.blockSize * 0.5f;

            for (int x = 0; x < settings.blocksX; x++)
            {
                for (int z = 0; z < settings.blocksZ; z++)
                {
                    Vector3 center = new Vector3(originX + x * settings.CellSize, 0f, originZ + z * settings.CellSize);
                    GenerateBlock(center, x, z);
                }
            }
        }

        private void GenerateBlock(Vector3 center, int blockX, int blockZ)
        {
            GameObject root = new GameObject($"Block_{blockX}_{blockZ}");
            root.transform.SetParent(transform, false);
            root.transform.position = center;

            CreateBox("Sidewalk", new Vector3(center.x, 0.11f, center.z), new Vector3(settings.blockSize, 0.22f, settings.blockSize), sidewalkMaterial).transform.SetParent(root.transform, true);

            int count = Mathf.Max(1, settings.buildingsPerBlockSide);
            float usable = settings.blockSize - 2f * settings.sidewalkWidth;
            float lotSize = usable / count;
            float footprint = lotSize * settings.lotCoverage;
            float start = -usable * 0.5f + lotSize * 0.5f;

            for (int lx = 0; lx < count; lx++)
            {
                for (int lz = 0; lz < count; lz++)
                {
                    float height = Random.Range(settings.minBuildingHeight, settings.maxBuildingHeight);
                    float widthScale = Random.Range(0.72f, 1f);
                    float depthScale = Random.Range(0.72f, 1f);
                    Vector3 position = center + new Vector3(start + lx * lotSize, height * 0.5f + 0.22f, start + lz * lotSize);
                    Vector3 scale = new Vector3(footprint * widthScale, height, footprint * depthScale);
                    Material material = ChooseBuildingMaterial();
                    GameObject building = CreateBox($"Building_{lx}_{lz}", position, scale, material);
                    building.transform.SetParent(root.transform, true);
                }
            }
        }

        private Material ChooseBuildingMaterial()
        {
            if (buildingMaterials == null || buildingMaterials.Length == 0) return null;
            return buildingMaterials[Random.Range(0, buildingMaterials.Length)];
        }

        private static GameObject CreateBox(string name, Vector3 position, Vector3 scale, Material material)
        {
            GameObject go = GameObject.CreatePrimitive(PrimitiveType.Cube);
            go.name = name;
            go.transform.position = position;
            go.transform.localScale = scale;
            if (material != null) go.GetComponent<Renderer>().sharedMaterial = material;
            return go;
        }
    }
}
