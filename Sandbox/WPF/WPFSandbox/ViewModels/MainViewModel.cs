using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Diagnostics;
using System.Collections.ObjectModel;

namespace WPFSandbox.ViewModels
{
    /// <summary>
    /// mainViewウィンドウに設定するデータコンテキスト
    /// </summary>
    internal class MainViewModel : NotificationObject
    {
        public MainViewModel()
        {
            _treeViewList = new ObservableCollection<TreeViewData>();
        }

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

        #region TreeView
        private int _listViewCount = 0;

        private DelegateCommand _addCommand;
        public DelegateCommand AddCommand
        {
            get
            {
                return _addCommand ?? (_addCommand = new DelegateCommand(
                    _ =>
                    {
                        _listViewCount++;
                        var data = new TreeViewData()
                        {
                            Name = "田中" + _listViewCount
                        };
                        _treeViewList.Add(data);
                        AddCommand.RaiseCanExecuteChanged();


                    }));
            }
        }

        private DelegateCommand _deleteCommand;
        public DelegateCommand DeleteCommand
        {
            get
            {
                return _deleteCommand ?? (_deleteCommand = new DelegateCommand(
                    p =>
                    {
                        _treeViewList.Remove(p as TreeViewData);
                        DeleteCommand.RaiseCanExecuteChanged();
                    }));
            }
        }

        public class TreeViewData
        {
            public string Name { get; set; }
        }

        private ObservableCollection<TreeViewData> _treeViewList;
        public ObservableCollection<TreeViewData> TreeViewList
        {
            get { return _treeViewList; }
            private set { SetProperty(ref _treeViewList, value); }
        }
        #endregion
    }
}
