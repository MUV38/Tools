using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ModelEditor.Model3d
{
    class Model3dViewModel
    {
        public Model3dViewModel()
        {
            _model = new Model3d();
        }

        #region プロパティ

        #endregion

        /// <summary>
        /// インポート
        /// </summary>
        /// <param name="fileName">ファイル名</param>
        /// <returns>インポート成功か</returns>
        public bool Import(string fileName)
        {
            return _model.Import(fileName);
        }

        private Model3d _model;
    }
}
