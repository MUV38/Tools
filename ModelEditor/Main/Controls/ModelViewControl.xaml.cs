using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using ModelEditor.Model3d;

namespace ModelEditor.Main.Controls
{
    /// <summary>
    /// Interaction logic for ModelViewControl.xaml
    /// </summary>
    public partial class ModelViewControl : UserControl
    {
        public ModelViewControl()
        {
            InitializeComponent();
        }

        #region プロパティ
        /// <summary>
        /// Meshの選択変更コールバック
        /// </summary>
        public Action<object, SelectionChangedEventArgs> MeshSelectionChangedCallback
        {
            get { return (Action<object, SelectionChangedEventArgs>)GetValue(MeshSelectionChangedCallbackProperty); }
            set { SetValue(MeshSelectionChangedCallbackProperty, value); }
        }
        public static readonly DependencyProperty MeshSelectionChangedCallbackProperty = DependencyProperty.Register("MeshSelectionChangedCallback", typeof(Action<object, SelectionChangedEventArgs>), typeof(ModelViewControl), new PropertyMetadata(null));
        
        /// <summary>
        /// Materialの選択変更コールバック
        /// </summary>
        public Action<object, SelectionChangedEventArgs> MaterialSelectionChangedCallback
        {
            get { return (Action<object, SelectionChangedEventArgs>)GetValue(MaterialSelectionChangedCallbackProperty); }
            set { SetValue(MaterialSelectionChangedCallbackProperty, value); }
        }
        public static readonly DependencyProperty MaterialSelectionChangedCallbackProperty = DependencyProperty.Register("MaterialSelectionChangedCallback", typeof(Action<object, SelectionChangedEventArgs>), typeof(ModelViewControl), new PropertyMetadata(null));
        #endregion

        #region イベント
        private void ListBoxMesh_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            MeshSelectionChangedCallback?.Invoke(sender, e);
        }
        private void ListBoxMaterial_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            MaterialSelectionChangedCallback?.Invoke(sender, e);
        }
        #endregion

    }
}
