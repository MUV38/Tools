using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ModelEditor.ViewModel
{
    class PropertyObject : INotifyPropertyChanged
    {
        /// <summary>
        /// プロパティ変更通知
        /// </summary>
        /// <param name="propertyName">プロパティ名</param>
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
        /// <typeparam name="T">プロパティの型</typeparam>
        /// <param name="target">設定先</param>
        /// <param name="value">値</param>
        /// <param name="propertyName">プロパティ名</param>
        /// <returns>プロパティを設定できたか</returns>
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

        #region INotifyPropertyChangedの実装
        public event PropertyChangedEventHandler PropertyChanged;
        #endregion

    }
}
