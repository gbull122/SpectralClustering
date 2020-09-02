using Prism.Events;

namespace ClusteringAppCore
{
    public class DataLoadedEvent : PubSubEvent<double[,]>
    {
    }
}
