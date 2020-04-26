using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Diagnostics;

namespace WPFSandbox.ViewModels
{
    /// <summary>
    /// mainViewウィンドウに設定するデータコンテキスト
    /// </summary>
    internal class MainViewModel : NotificationObject
    {
        private string _upperSting;

        /// <summary>
        /// 大文字にした文字列
        /// </summary>
        public string UpperString
        {
            get { return _upperSting; }
            private set
            {
                if (_upperSting != value)
                {
                    SetProperty(ref _upperSting, value);
                }
            }
        }

        private string _inputString;

        public string InputString
        {
            get { return _inputString; }
            set
            {
                if (_inputString != value)
                {
                    if (SetProperty(ref _inputString, value))
                    {
                        // 大文字
                        UpperString = _inputString.ToUpper();

                        // コマンド実行可能状態の変更通知
                        ClearCommand.RaiseCanExecuteChanged();

                        // デバッグ出力
                        Debug.WriteLine("UpperString = " + UpperString);
                    }
                }
            }
        }

        private DelegateCommand _clearCommand;
        
        public DelegateCommand ClearCommand
        {
            get
            {
                if (_clearCommand == null)
                {
                    _clearCommand = new DelegateCommand(
                        _ =>  InputString = "",
                        _ => !string.IsNullOrEmpty(InputString)
                    );
                }
                return _clearCommand;
            }
        }
    }
}
