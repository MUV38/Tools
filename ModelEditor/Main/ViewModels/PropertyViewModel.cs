using ModelEditor.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ModelEditor.Main.ViewModels
{
    class PropertyViewModel
    {
        public PropertyViewModel(CommonViewModel commonViewModel)
        {
            _commonViewModel = commonViewModel;
        }

        private CommonViewModel _commonViewModel;
    }
}
