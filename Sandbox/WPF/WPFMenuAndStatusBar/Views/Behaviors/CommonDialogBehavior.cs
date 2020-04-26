using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows;
using Microsoft.Win32;

namespace WPFMenuAndStatusBar.Views.Behaviors
{
    internal class CommonDialogBehavior
    {
        #region Callback 添付プロパティ
        /// <summary>
        /// Callbackプロパティ
        /// </summary>
        public static readonly DependencyProperty CallbackProperty = DependencyProperty.RegisterAttached("Callback", typeof(Action<bool, string>), typeof(CommonDialogBehavior), new PropertyMetadata(null, OnCallbackPropertyChanged));

        /// <summary>
        /// Callbackプロパティ取得
        /// </summary>
        public static Action<bool, string> GetCallback(DependencyObject target)
        {
            return (Action<bool, string>)target.GetValue(CallbackProperty);
        }

        /// <summary>
        /// Callbackプロパティ設定
        /// </summary>
        public static void SetCallback(DependencyObject target, Action<bool, string> value)
        {
            target.SetValue(CallbackProperty, value);
        }
        #endregion

        #region TiTle 添付プロパティ
        /// <summary>
        /// Titleプロパティ
        /// </summary>
        public static readonly DependencyProperty TitleProperty = DependencyProperty.RegisterAttached("Title", typeof(string), typeof(CommonDialogBehavior), new PropertyMetadata("ファイルを開く"));

        /// <summary>
        /// Titleプロパティ取得
        /// </summary>
        public static string GetTitle(DependencyObject target)
        {
            return (string)target.GetValue(TitleProperty);
        }

        /// <summary>
        /// Titleプロパティ設定
        /// </summary>
        public static void SetTitle(DependencyObject target, string value)
        {
            target.SetValue(TitleProperty, value);
        }
        #endregion

        #region Filter 添付プロパティ
        /// <summary>
        /// Filterプロパティ
        /// </summary>
        public static readonly DependencyProperty FilterProperty = DependencyProperty.RegisterAttached("Filter", typeof(string), typeof(CommonDialogBehavior), new PropertyMetadata("すべてのファイル(*.*)|*.*"));
        
        /// <summary>
        /// Filterプロパティ取得 
        /// </summary>
        public static string GetFilter(DependencyObject target)
        {
            return (string)target.GetValue(FilterProperty);
        }

        /// <summary>
        /// FIlterプロパティ設定
        /// </summary>
        public static void SetFilter(DependencyObject target, string value)
        {
            target.SetValue(FilterProperty, value);
        }
        #endregion

        #region MultiSelect 添付プロパティ
        /// <summary>
        /// Mutiselectプロパティ
        /// </summary>
        public static readonly DependencyProperty MultiselectProperty = DependencyProperty.RegisterAttached("Multiselect", typeof(bool), typeof(CommonDialogBehavior), new PropertyMetadata(true));

        /// <summary>
        /// Multiselectプロパティ取得
        /// </summary>
        public static bool GetMultiselect(DependencyObject target)
        {
            return (bool)target.GetValue(MultiselectProperty);
        }

        /// <summary>
        /// Multiselectプロパティ設定
        /// </summary>
        public static void SetMultiselect(DependencyObject target, bool value)
        {
            target.SetValue(MultiselectProperty, value);
        }
        #endregion

        private static void OnCallbackPropertyChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            var callback = GetCallback(sender);
            if (callback != null)
            {
                var diag = new OpenFileDialog()
                {
                    Title = GetTitle(sender),
                    Filter = GetFilter(sender),
                    Multiselect = GetMultiselect(sender)
                };
                var owner = Window.GetWindow(sender);
                var result = diag.ShowDialog(owner);
                callback(result.Value, diag.FileName);
            }
        }
    }
}
