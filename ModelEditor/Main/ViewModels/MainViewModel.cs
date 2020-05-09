using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ModelEditor.ViewModel;
using ModelEditor.Command;
using ModelEditor.Model3d;
using System.Collections.ObjectModel;

namespace ModelEditor.Main.ViewModels
{
    /// <summary>
    /// メインウィンドウのビューモデル
    /// </summary>
    class MainViewModel : PropertyObject
    {
        public MainViewModel()
        {
            _commonViewModel = new CommonViewModel();
            _menuViewModel = new MenuViewModel(CommonViewModel);
            _modelViewModel = new ModelViewModel(CommonViewModel);
            _propertyViewModel = new PropertyViewModel(CommonViewModel);
        }

        #region ビューモデル
        /// <summary>
        /// 共通のビューモデル
        /// </summary>
        private CommonViewModel _commonViewModel;
        public CommonViewModel CommonViewModel
        {
            get { return _commonViewModel; }
        }
        /// <summary>
        /// メニュービューモデル
        /// </summary>
        private MenuViewModel _menuViewModel;
        public MenuViewModel MenuViewModel
        {
            get { return _menuViewModel; }
        }
        /// <summary>
        /// モデルビューのビューモデル
        /// </summary>
        private ModelViewModel _modelViewModel;
        public ModelViewModel ModelViewModel
        {
            get { return _modelViewModel; }
        }
        /// <summary>
        /// プロパティのビューモデル
        /// </summary>
        private PropertyViewModel _propertyViewModel;
        public PropertyViewModel PropertyViewModel
        {
            get { return _propertyViewModel; }
        }
        #endregion
    }
}
