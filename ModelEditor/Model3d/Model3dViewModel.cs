using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Collections.ObjectModel;
using ModelEditor.ViewModel;

namespace ModelEditor.Model3d
{
    class Model3dViewModel : PropertyObject
    {
        public Model3dViewModel()
        {
            _model = new Model3d();
        }

        #region プロパティ
        private Model3d _model;
        public Model3dData ModelData
        {
            get { return _model.Data; }
        }
        public ObservableCollection<MeshData> MeshDatas
        {
            get { return ModelData?.Meshes; }
        }
        public ObservableCollection<MaterialData> MaterialDatas
        {
            get { return ModelData?.Materials; }
        }
        private void RaisePropertyChangedModel()
        {
            RaisePropertyChanged("ModelData");
            RaisePropertyChanged("MeshDatas");
            RaisePropertyChanged("MaterialDatas");
        }
        #endregion

        /// <summary>
        /// インポート
        /// </summary>
        /// <param name="fileName">ファイル名</param>
        /// <returns>インポート成功か</returns>
        public bool Import(string fileName)
        {
            bool result = _model.Import(fileName);
            if (result)
            {
                RaisePropertyChangedModel();
            }

            return result;
        }

    }
}
