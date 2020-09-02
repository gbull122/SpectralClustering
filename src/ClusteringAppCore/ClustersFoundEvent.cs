using Prism.Events;

namespace ClusteringAppCore
{
    public class ClustersFoundEvent : PubSubEvent<int[][]>
    {
    }
}
