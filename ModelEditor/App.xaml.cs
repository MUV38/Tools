using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

using ModelEditor.Main.Views;
using ModelEditor.Main.ViewModels;

namespace ModelEditor
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        /// <summary>
        /// スタートアップ
        /// </summary>
        /// <param name="e">イベント引数</param>
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            // ビューとビューモデルの生成と関連付け
            var view = new MainView();
            var viewModel = new MainViewModel();
            view.DataContext = viewModel;

            // ビュー表示
            view.Show();
        }
    }
}
