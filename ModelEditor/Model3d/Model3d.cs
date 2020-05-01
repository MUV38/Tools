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

            try
            {
                using (var streamReader = new StreamReader(fileName))
                {
                    string json = streamReader.ReadToEnd();
                    // _modelData = JsonSerializer.Deserialize<Model3dData>(json);
                    var document = System.Text.Json.JsonDocument.Parse(json);

                    _modelData = new Model3dData();
                    _modelData.ParseJsonElement(document.RootElement);

                    System.Diagnostics.Debug.WriteLine("test");
                }
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.Message);
                return false;
            }

            return true;
        }

        private Model3dData _modelData;
    }
}
