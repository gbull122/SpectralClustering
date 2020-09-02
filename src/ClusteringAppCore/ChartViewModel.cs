using OxyPlot;
using OxyPlot.Series;
using Prism.Events;
using Prism.Mvvm;

namespace ClusteringAppCore
{
    public class ChartViewModel : BindableBase
    {

        private Model plotModel;
        private IEventAggregator eventAggregator;
        private double[,] pointData;

        public Model PlotModel
        {
            get { return plotModel; }
            set
            {
                plotModel = value;
                RaisePropertyChanged("PlotModel");
            }
        }

        public ChartViewModel(IEventAggregator eventAgg)
        {
            eventAggregator = eventAgg;

            eventAggregator.GetEvent<DataLoadedEvent>().Subscribe(PlotData);
            eventAggregator.GetEvent<ClustersFoundEvent>().Subscribe(PlotClusters);

        }

        private void PlotData(double[,] data)
        {
            pointData = data;
            var plotModel = new PlotModel();
            plotModel.Title = "Data";

            var scatterSeries = new ScatterSeries();
            scatterSeries.MarkerType = MarkerType.Circle;

            for (int row = 0; row < data.GetLength(0); row++)
            {
                var scatterPoint = new ScatterPoint(data[row, 0], data[row, 1]);
                scatterSeries.Points.Add(scatterPoint);
            }

            plotModel.Series.Add(scatterSeries);

            PlotModel = plotModel;
        }

        private void PlotClusters(int[][] clusters)
        {
            var plotModel = new PlotModel();
            plotModel.Title = "Clusters";

            for (int cluster = 0; cluster < clusters.GetLength(0); cluster++)
            {
                var scatterSeries = new ScatterSeries();
                scatterSeries.MarkerType = MarkerType.Circle;

                var clusterPoints = clusters[cluster];
                for (int p = 0; p < clusterPoints.Length; p++)
                {
                    var dataPointIndex = clusterPoints[p];

                    var scatterPoint = new ScatterPoint(pointData[dataPointIndex, 0], pointData[dataPointIndex, 1], 5, cluster);
                    scatterSeries.Points.Add(scatterPoint);
                }
                plotModel.Series.Add(scatterSeries);

            }

            PlotModel = plotModel;
        }
    }
}
