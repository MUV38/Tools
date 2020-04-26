using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPFItemsConrol.Models
{
    /// <summary>
    /// 性別
    /// </summary>
    internal enum Gender
    {
        Male,
        Female,
        Unknown,
    }

    /// <summary>
    /// 人
    /// </summary>
    internal class Person
    {
        /// <summary>
        /// 苗字
        /// </summary>
        public string FamilyName { get; set; }
        /// <summary>
        /// 名前
        /// </summary>
        public string FirstName { get; set; }
        /// <summary>
        /// 氏名
        /// </summary>
        public string FullName { get { return FamilyName + FirstName; } }
        /// <summary>
        /// 氏名
        /// </summary>
        public Gender Gender { get; set; }
        /// <summary>
        /// 年齢
        /// </summary>
        public int Age { get; set; }
        /// <summary>
        /// 認証済みかどうか
        /// </summary>
        public bool IsAuthenticated { get; set; }
    }
}
