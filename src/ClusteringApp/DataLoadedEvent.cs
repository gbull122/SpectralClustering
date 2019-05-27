using Prism.Events;

namespace ClusteringApp
{
    public class DataLoadedEvent:PubSubEvent<double[,]>
    {
    }
}
