using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using Clustering;
using Prism.Commands;
using Prism.Mvvm;

namespace ClusteringApp
{
    public class ControlPanelViewModel:BindableBase
    {

        public DelegateCommand ClusterCommand { get; private set; }


        public ControlPanelViewModel()
        {
            ClusterCommand = new DelegateCommand(Cluster);
        }

        private void Cluster()
        {
            Class1 clustering = new Class1();

            var data = "..\\..\\..\\..\\data\\0.txt";
            var clusters = clustering.DoCluster(data);
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
