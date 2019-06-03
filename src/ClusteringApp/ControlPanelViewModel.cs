using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Threading;

namespace ClusteringApp
{
    public class ControlPanelViewModel:BindableBase
    {
        private IEventAggregator eventAggregator;
        private string dataFilePath = "..\\..\\..\\..\\data\\5.txt";
        private string loadedFileName;
        private bool useKmeans;
        private bool useSpectral;
        private double[,] data;
        private string numClusters;
        private bool progressIndeterminate;
        internal Dispatcher uiDispatcher;

        public DelegateCommand ClusterCommand { get; private set; }
        public DelegateCommand LoadDataCommand { get; private set; }
        public DelegateCommand<string> PreviewTextCommand { get; private set; }

        public string NumClusters
        {
            get { return numClusters; }
            set
            {
                numClusters = value;
                RaisePropertyChanged("NumClusters");
            }
        }

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

        public bool ProgressIndeterminate
        {
            get { return progressIndeterminate; }
            set
            {
                progressIndeterminate = value;
                RaisePropertyChanged("ProgressIndeterminate");
            }
        }

        public ControlPanelViewModel(IEventAggregator eventAgg)
        {
            ClusterCommand = new DelegateCommand(Cluster,CanCluster);
            LoadDataCommand = new DelegateCommand(LoadData);
            eventAggregator = eventAgg;
            numClusters = "4";
            useSpectral = true;

            uiDispatcher = Dispatcher.CurrentDispatcher;
        }

        private bool CanCluster()
        {
            return data != null;
        }

        private void LoadData()
        {
            ProgressIndeterminate = true;
            data = LoadCsvFile(dataFilePath);
            eventAggregator.GetEvent<DataLoadedEvent>().Publish(data);
            ClusterCommand.RaiseCanExecuteChanged();
            ProgressIndeterminate = false;
        }

        private async void Cluster()
        {
            StartProgress();

            await Task.Run(() => PerformClusteringAsync());

            StopProgress();
        }

        private void StopProgress()
        {
            ProgressIndeterminate = false;
        }

        private void StartProgress()
        {
            ProgressIndeterminate = true;
        }

        private async Task PerformClusteringAsync()
        {
            Clusters clustering = new Clusters();
            int.TryParse(numClusters, out int maxClusters);

            GCHandle handle = GCHandle.Alloc(data, GCHandleType.Pinned);
            IntPtr pointer = handle.AddrOfPinnedObject();

            var clusters = clustering.DoCluster(pointer,2,data.GetLength(0), maxClusters);
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

        public void PreviewText(object sender, TextCompositionEventArgs e)
        {
            e.Handled = !IsTextAllowed(e.Text);
        }

        private bool IsTextAllowed(string text)
        {
            Regex regex = new Regex("[^0-9.-]+"); 
            return !regex.IsMatch(text);
        }
    }
}
