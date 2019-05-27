using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using Clustering;
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;

namespace ClusteringApp
{
    public class ControlPanelViewModel:BindableBase
    {
        private IEventAggregator eventAggregator;
        private string dataFilePath = "..\\..\\..\\..\\data\\ClusterTest.csv";
        private string loadedFileName;
        private bool useKmeans;
        private bool useSpectral;

        public DelegateCommand ClusterCommand { get; private set; }
        public DelegateCommand LoadDataCommand { get; private set; }

        public string LoadedFileName
        {
            get { return loadedFileName; }
            set
            {
                loadedFileName = value;
                RaisePropertyChanged("LoadedFileName");
            }
        }

        public bool UseKmeans
        {
            get { return useKmeans; }
            set
            {
                useKmeans = value;
                RaisePropertyChanged("UseKmeans");
            }
        }

        public bool UseSpectral
        {
            get { return useSpectral; }
            set
            {
                useSpectral = value;
                RaisePropertyChanged("UseSpectral");
            }
        }

        public ControlPanelViewModel(IEventAggregator eventAgg)
        {
            ClusterCommand = new DelegateCommand(Cluster);
            LoadDataCommand = new DelegateCommand(LoadData);
            eventAggregator = eventAgg;
        }

        private void LoadData()
        {
            var data = LoadCsvFile(dataFilePath);
            eventAggregator.GetEvent<DataLoadedEvent>().Publish(data);
        }

        private void Cluster()
        {
            Class1 clustering = new Class1();

            var clusters = clustering.DoCluster(dataFilePath);
            eventAggregator.GetEvent<ClustersFoundEvent>().Publish(clusters);
        }

        public double[,] LoadCsvFile(string filePath)
        {
            var reader = new StreamReader(File.OpenRead(filePath));
            List<double[]> data = new List<double[]>();

            while (!reader.EndOfStream)
            {
                var lineSplit = reader.ReadLine().Split(',');
                var dataValues = StringArrayToDouble(lineSplit);

                data.Add(dataValues);
            }

            double[,] dataArray = new double[data.Count, data[0].Count()];
            for (int row = 0; row < data.Count; row++)
            {
                for (int col = 0; col < data[row].Count(); col++)
                {
                    dataArray[row, col] = data[row][col];
                }
            }
            return dataArray;
        }

        public double[] StringArrayToDouble(string[] dataStrings)
        {
            double[] dataValues = (dataStrings)
                                 .Cast<object>()
                                 .Select(x => double.Parse(x.ToString(), CultureInfo.InvariantCulture))
                                 .ToArray<double>();
            return dataValues;
        }
    }
}
