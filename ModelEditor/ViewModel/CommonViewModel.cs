using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ModelEditor.Model3d;

namespace ModelEditor.ViewModel
{
    class CommonViewModel : PropertyObject
    {
        public CommonViewModel()
        {
            Model3dViewModel = new Model3dViewModel();
        }

        private Model3dViewModel _model3dViewModel;
        public Model3dViewModel Model3dViewModel
        {
            get { return _model3dViewModel; }
            private set { _model3dViewModel = value; }
        }
    }
}
