using Prism.Events;

namespace ClusteringApp
{
    public class ClustersFoundEvent:PubSubEvent<int[][]>
    {
    }
}
