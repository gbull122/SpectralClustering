using Prism.Mvvm;
using Prism.Regions;

namespace ClusteringAppCore
{
    public class MainWindowViewModel : BindableBase
    {
        private string title = "Spectral Clustering";
        private IRegionManager regionManager;

        public string Title
        {
            get { return title; }
            set { SetProperty(ref title, value); }
        }

        public MainWindowViewModel(IRegionManager regManager)
        {
            regionManager = regManager;


            regionManager.RegisterViewWithRegion("ControlRegion", typeof(ControlPanelView));
            regionManager.RegisterViewWithRegion("ChartRegion", typeof(ChartView));
        }
    }
}