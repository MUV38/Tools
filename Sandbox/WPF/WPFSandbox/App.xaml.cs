using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace WPFSandbox
{
    using Views;
    using ViewModels;

    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            // view
            var v = new MainView();

            // view model
            var vm = new MainViewModel();

            // viewにview modelを設定
            v.DataContext = vm;

            // ウィドウ表示
            v.Show();
        }
    }
}
