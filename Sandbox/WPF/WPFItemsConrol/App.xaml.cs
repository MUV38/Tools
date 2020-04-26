using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace WPFItemsConrol
{
    using Views;
    using ViewModels;
    using Models;

    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            var view = new MainView();
            var viewModel = new MainViewModel();
            view.DataContext = viewModel;

            view.Show();
        }
    }
}
