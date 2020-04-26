using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace WPFMenuAndStatusBar.Views.Behaviors
{
    class OpenDialogBehavior
    {
        #region DataContext 添付プロパティ
        public static readonly DependencyProperty DataContextProperty = DependencyProperty.RegisterAttached("DataContext", typeof(object), typeof(OpenDialogBehavior), new PropertyMetadata(null));

        public static object GetDataContext(DependencyObject target)
        {
            return target.GetValue(DataContextProperty);
        }

        public static void SetDataContext(DependencyObject target, object value)
        {
            target.SetValue(DataContextProperty, value);
        }
        #endregion

        #region WindowType 添付プロパティ
        public static readonly DependencyProperty WindowTypeProperty = DependencyProperty.RegisterAttached("WindowType", typeof(Type), typeof(OpenDialogBehavior), new PropertyMetadata(null));

        public static Type GetWindowType(DependencyObject target)
        {
            return (Type)target.GetValue(WindowTypeProperty);
        }

        public static void SetWindowType(DependencyObject target, Type value)
        {
            target.SetValue(WindowTypeProperty, value);
        }
        #endregion

        #region Callback 添付プロパティ
        public static readonly DependencyProperty CallbackProperty = DependencyProperty.RegisterAttached("Callback", typeof(Action<bool>), typeof(OpenDialogBehavior), new PropertyMetadata(null, OnCallbackPropertyChanged));

        public static Action<bool> GetCallback(DependencyObject target)
        {
            return (Action<bool>)target.GetValue(CallbackProperty);
        }

        public static void SetCallback(DependencyObject target, Action<bool> value)
        {
            target.SetValue(CallbackProperty, value);
        }
        #endregion

        private static void OnCallbackPropertyChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            var callback = GetCallback(sender);
            if (callback != null)
            {
                var type = GetWindowType(sender);
                var obj = type.InvokeMember(null, System.Reflection.BindingFlags.CreateInstance, null, null, null);
                var child = obj as Window;
                if (child != null)
                {
                    child.DataContext = GetDataContext(sender);
                    var result = child.ShowDialog();
                    callback(result.Value);
                }
            }
        }
    }
}
