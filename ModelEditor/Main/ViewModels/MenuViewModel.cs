using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ModelEditor.Command;
using ModelEditor.ViewModel;

namespace ModelEditor.Main.ViewModels
{
    class MenuViewModel : PropertyObject
    {
        public MenuViewModel(CommonViewModel commonViewModel)
        {
            _commonViewModel = commonViewModel;
        }

        #region ファイルを開く
        private CommandObject _openFileDialog;
        public CommandObject OpenFileDialog
        {
            get
            {
                return _openFileDialog ?? (_openFileDialog = new CommandObject(
                    _ =>
                    {
                        OpenFileDialogCallback = OnOpenFileDialog;
                    }));
            }
        }

        private Action<bool, string> _openFileDialogCallback;
        public Action<bool, string> OpenFileDialogCallback
        {
            get { return _openFileDialogCallback; }
            set { SetProperty(ref _openFileDialogCallback, value); }
        }
        /// <summary>
        /// ファイルオープンダイアログのイベント
        /// </summary>
        /// <param name="result">オープン成功か</param>
        /// <param name="filename">ファイル名</param>
        private void OnOpenFileDialog(bool result, string filename)
        {
            OpenFileDialogCallback = null;
            System.Diagnostics.Debug.WriteLine("result:{0} filename:{1}", result, filename);
        }
        #endregion

        #region ファイルをインポート
        private CommandObject _importFileDialog;
        public CommandObject ImportFileDialog
        {
            get
            {
                return _importFileDialog ?? (_importFileDialog = new CommandObject(
                    _ =>
                    {
                        ImportFileDialogCallback = OnImportFileDialog;
                    }));
            }
        }

        private Action<bool, string> _importFileDialogCallback;
        public Action<bool, string> ImportFileDialogCallback
        {
            get { return _importFileDialogCallback; }
            set { SetProperty(ref _importFileDialogCallback, value); }
        }
        private void OnImportFileDialog(bool result, string filename)
        {
            ImportFileDialogCallback = null;
            System.Diagnostics.Debug.WriteLine("result:{0} filename:{1}", result, filename);

            if (result)
            {
                _commonViewModel.Model3dViewModel?.Import(filename);
            }
        }
        #endregion


        private CommonViewModel _commonViewModel;
    }
}
