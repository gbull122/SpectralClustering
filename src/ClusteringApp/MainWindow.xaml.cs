using Clustering;
using System.Windows;

namespace ClusteringApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            Class1 clustering = new Class1();

            var clusterCount = clustering.DoCluster();

        }
    }
}
