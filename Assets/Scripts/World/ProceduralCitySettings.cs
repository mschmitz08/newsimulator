using UnityEngine;

namespace NewSimulator.World
{
    [CreateAssetMenu(menuName = "New Simulator/Procedural City Settings", fileName = "ProceduralCitySettings")]
    public sealed class ProceduralCitySettings : ScriptableObject
    {
        [Header("Layout")]
        [Min(1)] public int blocksX = 4;
        [Min(1)] public int blocksZ = 4;
        [Min(20f)] public float blockSize = 70f;
        [Min(4f)] public float roadWidth = 14f;
        [Min(1f)] public float sidewalkWidth = 4f;

        [Header("Buildings")]
        [Min(1)] public int buildingsPerBlockSide = 3;
        [Min(3f)] public float minBuildingHeight = 10f;
        [Min(4f)] public float maxBuildingHeight = 65f;
        [Range(0.45f, 0.9f)] public float lotCoverage = 0.72f;

        [Header("Generation")]
        public int randomSeed = 20261022;
        public bool generateRoadMarkings = true;

        public float CellSize => blockSize + roadWidth;
    }
}
