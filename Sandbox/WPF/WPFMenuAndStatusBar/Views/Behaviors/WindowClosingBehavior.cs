using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.ComponentModel;
using System.Windows;

namespace WPFMenuAndStatusBar.Views.Behaviors
{
    internal class WindowClosingBehavior
    {
        #region Callback 添付プロパティ
        public static readonly DependencyProperty CallbackProperty = DependencyProperty.RegisterAttached("Callback", typeof(Func<bool>), typeof(WindowClosingBehavior), new PropertyMetadata(null, OnIsEnablePropertyChanged));
        
        public static Func<bool> GetCallback(DependencyObject target)
        {
            return (Func<bool>)target.GetValue(CallbackProperty);
        }

        public static void SetCallback(DependencyObject target, Func<bool> value)
        {
            target.SetValue(CallbackProperty, value);
        }
        #endregion

        private static void OnIsEnablePropertyChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            var w = sender as Window;
            if (w != null)
            {
                var callback = GetCallback(sender);
                if ((callback != null) && (e.OldValue == null))
                {
                    w.Closing += OnClosing;
                }
                else if (callback == null)
                {
                    w.Closing -= OnClosing;
                }
            }
        }

        private static void OnClosing(object sender, CancelEventArgs e)
        {
            var callback = GetCallback(sender as DependencyObject);
            if (callback != null)
            {
                e.Cancel = !callback();
            }
        }
    }
}
