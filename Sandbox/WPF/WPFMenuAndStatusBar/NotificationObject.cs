using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace WPFMenuAndStatusBar
{
    /// <summary>
    /// 通知オブジェクト
    /// </summary>
    internal abstract class NotificationObject : INotifyPropertyChanged
    {
        #region INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// PropertyChangedイベント
        /// </summary>
        protected void RaisePropertyChanged([CallerMemberName]string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        /// <summary>
        /// プロパティ設定
        /// </summary>
        protected bool SetProperty<T>(ref T target, T value, [CallerMemberName]string propertyName = null)
        {
            if (Equals(target, value))
            {
                return false;
            }

            target = value;
            RaisePropertyChanged(propertyName);

            return true;
        }
        #endregion
    }
}
