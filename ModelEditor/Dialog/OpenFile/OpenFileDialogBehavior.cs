using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

using Microsoft.Win32;

namespace ModelEditor.Dialog.OpenFile
{
    class OpenFileDialogBehavior
    {

        #region プロパティ
        /// <summary>
        /// TiTleプロパティ
        /// </summary>
        public static readonly DependencyProperty TitleProperty = DependencyProperty.RegisterAttached("Title", typeof(string), typeof(OpenFileDialogBehavior), new PropertyMetadata(null));
        /// <summary>
        /// Filterプロパティ
        /// </summary>
        public static readonly DependencyProperty FilterProperty = DependencyProperty.RegisterAttached("Filter", typeof(string), typeof(OpenFileDialogBehavior), new PropertyMetadata(null));
        /// <summary>
        /// Multiselectプロパティ
        /// </summary>
        public static readonly DependencyProperty MultiselectProperty = DependencyProperty.RegisterAttached("Multiselect", typeof(bool), typeof(OpenFileDialogBehavior), new PropertyMetadata(null));
        /// <summary>
        /// Callbackプロパティ
        /// </summary>
        public static readonly DependencyProperty CallbackProperty = DependencyProperty.RegisterAttached("Callback", typeof(Action<bool, string>), typeof(OpenFileDialogBehavior), new PropertyMetadata(null, OnCallbackPropertyChanged));
        #endregion

        #region TiTle
        public static string GetTitle(DependencyObject target)
        {
            return (string)target.GetValue(TitleProperty);
        }
        public static void SetTitle(DependencyObject target, string value)
        {
            target.SetValue(TitleProperty, value);
        }
        #endregion

        #region Filter
        public static string GetFilter(DependencyObject target)
        {
            return (string)target.GetValue(FilterProperty);
        }
        public static void SetFilter(DependencyObject target, string value)
        {
            target.SetValue(FilterProperty, value);
        }
        #endregion

        #region Multiselect
        public static bool GetMultiselect(DependencyObject target)
        {
            return (bool)target.GetValue(MultiselectProperty);
        }
        public static void SetMultiselect(DependencyObject target, bool value)
        {
            target.SetValue(MultiselectProperty, value);
        }
        #endregion

        #region Callback
        public static Action<bool, string> GetCallback(DependencyObject target)
        {
            return (Action<bool, string>)target.GetValue(CallbackProperty);
        }
        public static void SetCallback(DependencyObject target, Action<bool, string> value)
        {
            target.SetValue(CallbackProperty, value);
        }
        /// <summary>
        /// Callbackプロパティ変更イベント
        /// </summary>
        /// <param name="sender">通知者</param>
        private static void OnCallbackPropertyChanged(DependencyObject sender, DependencyPropertyChangedEventArgs _)
        {
            var callback = GetCallback(sender);
            if (callback != null)
            {
                var dialog = new OpenFileDialog()
                {
                    Title = GetTitle(sender),
                    Filter = GetFilter(sender),
                    Multiselect = GetMultiselect(sender)
                };
                var owner = Window.GetWindow(sender);
                var result = dialog.ShowDialog(owner);
                callback(result.Value, dialog.FileName);
            }
        }
        #endregion
    }
}
