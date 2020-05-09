using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ModelEditor.Model3d;
using ModelEditor.ViewModel;

namespace ModelEditor.Main.ViewModels
{
    class ModelViewModel : PropertyObject
    {
        public ModelViewModel(CommonViewModel commonViewModel)
        {
            _commonViewModel = commonViewModel;

            Model3dViewModel.PropertyChanged += OnModelPropertyChanged;
        }

        #region プロパティ
        /// <summary>
        /// モデル
        /// </summary>
        public Model3dData ModelData
        {
            get { return Model3dViewModel.ModelData; }
        }
        /// <summary>
        /// メッシュ
        /// </summary>
        public ObservableCollection<MeshData> MeshDatas
        {
            get { return ModelData?.Meshes; }
        }
        /// <summary>
        /// マテリアル
        /// </summary>
        public ObservableCollection<MaterialData> MaterialDatas
        {
            get { return ModelData?.Materials; }
        }
        /// <summary>
        /// モデル3dのビューモデル
        /// </summary>
        public Model3dViewModel Model3dViewModel
        {
            get { return _commonViewModel.Model3dViewModel; }
        }
        #endregion

        /// <summary>
        /// モデルのプロパティ変更
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void OnModelPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            RaisePropertyChanged(e.PropertyName);
        }

        private CommonViewModel _commonViewModel;
    }
}
