using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using WPFMenuAndStatusBar.Models;

namespace WPFMenuAndStatusBar.ViewModels
{
    class VersionViewModel : NotificationObject
    {
        public string ProductName
        {
            get { return ProductInfo.Product; }
        }

        public string Title
        {
            get { return ProductInfo.Title; }
        }

        public string Version
        {
            get { return "Ver." + ProductInfo.VersionString; }
        }

        public string Copyright
        {
            get { return ProductInfo.Copyright; }
        }
    }
}
