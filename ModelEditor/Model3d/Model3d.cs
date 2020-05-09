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
        #region プロパティ
        public Model3dData Data
        {
            get { return _modelData; }
        }
        #endregion

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
                    // 全文字列読み取り
                    string json = streamReader.ReadToEnd();
                    if (json == "")
                    {
                        throw new Exception("Failed Read json.");
                    }

                    // json全体のパース
                    var document = System.Text.Json.JsonDocument.Parse(json);
                    if (document == null)
                    {
                        throw new Exception("Failed parse json.");
                    }

                    // モデルデータ構築
                    var modelData = new Model3dData();
                    bool result = modelData.ParseJsonElement(document.RootElement);
                    if (!result)
                    {
                        throw new Exception("Failed parse json element.");
                    }
                    _modelData = modelData;
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
