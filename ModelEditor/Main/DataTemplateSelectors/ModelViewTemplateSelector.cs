using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace ModelEditor.Main.DataTemplateSelectors
{
    class ModelViewTemplateSelector : DataTemplateSelector
    {
        /// <summary>
        /// 空表示用テンプレート
        /// </summary>
        public DataTemplate EmptyTemplate { get; set; }
        /// <summary>
        /// メッシュ表示用テンプレート
        /// </summary>
        public DataTemplate MeshTemplate { get; set; }
        /// <summary>
        /// マテリアル表示用テンプレート
        /// </summary>
        public DataTemplate MaterialTemplate { get; set; }

        /// <summary>
        /// テンプレートの選択
        /// </summary>
        /// <param name="item"></param>
        /// <param name="container"></param>
        /// <returns></returns>
        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            return EmptyTemplate;
        }
    }
}
