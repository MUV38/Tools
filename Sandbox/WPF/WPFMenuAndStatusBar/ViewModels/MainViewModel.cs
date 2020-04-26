using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Timers;

namespace WPFMenuAndStatusBar.ViewModels
{
    internal class MainViewModel :NotificationObject
    {
        #region ファイルを開く
        private DelegateCommand _openFileCommand;
        public DelegateCommand OpenFileCommand
        {
            get
            {
                return _openFileCommand ?? (_openFileCommand = new DelegateCommand(
                    _ =>
                    {
                        DialogCallback = OnDialigCallback;
                    }));
            }
        }
        #endregion

        #region アプリを終了
        public Func<bool> ClosingCallback
        {
            get { return OnExit; }
        }

        private DelegateCommand _exitCommand;
        public DelegateCommand ExitCommand
        {
            get
            {
                return _exitCommand ?? (_exitCommand = new DelegateCommand(
                    _ =>
                    {
                        OnExit();
                    }));
            }
        }

        private bool OnExit()
        {
            //if (_counter < 3)
            //{
            //    _counter++;
            //    return false;
            //}
            App.Current.Shutdown();
            return true;
        }

        //private int _counter;
        #endregion

        #region バージョン情報
        private VersionViewModel _versionViewModel = new VersionViewModel();
        public VersionViewModel VersionViewModel
        {
            get { return _versionViewModel; }
        }

        private DelegateCommand _versionDialogCommand;
        public DelegateCommand VersionDialogCommand
        {
            get
            {
                return _versionDialogCommand ?? (_versionDialogCommand = new DelegateCommand(
                    _ =>
                    {
                        VersionDialogCallback = OnVersionDialog;
                    }));
            }
        }

        private Action<bool> _versionDialogCallback;
        public Action<bool> VersionDialogCallback
        {
            get { return _versionDialogCallback; }
            private set { SetProperty(ref _versionDialogCallback, value); }
        }

        private void OnVersionDialog(bool result)
        {
            VersionDialogCallback = null;
            System.Diagnostics.Debug.WriteLine(result);
        }
        #endregion

        #region 現在時刻
        private Timer _timer;
        private DateTime _currentTime;
        public DateTime CurrentTime
        {
            get
            {
                if (_timer == null)
                {
                    _currentTime = DateTime.Now;

                    _timer = new Timer(1000);
                    _timer.Elapsed += (_, __) =>
                    {
                        CurrentTime = DateTime.Now;
                    };
                    _timer.Start();
                }
                return _currentTime;
            }
            private set { SetProperty(ref _currentTime, value); }
        }
        #endregion

        private Action<bool, string> _dialogCallback;
        public Action<bool, string> DialogCallback
        {
            get { return _dialogCallback; }
            private set { SetProperty(ref _dialogCallback, value); }
        }

        private void OnDialigCallback(bool isOk, string filePath)
        {
            DialogCallback = null;
            System.Diagnostics.Debug.WriteLine("isOk = {0}, filePath = {1}", isOk, filePath);
        }
    }
}
