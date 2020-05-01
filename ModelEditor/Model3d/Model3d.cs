using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Text.Json;

namespace ModelEditor.Model3d
{
    class Model3d
    {
        /// <summary>
        /// インポート
        /// </summary>
        /// <param name="fileName">ファイル名</param>
        /// <returns>インポート成功か</returns>
        public bool Import(string fileName)
        {
            // 拡張子チェック
            if (Path.GetExtension(fileName) != ".json")
            {
                return false;
            }

            return true;
        }
    }
}
