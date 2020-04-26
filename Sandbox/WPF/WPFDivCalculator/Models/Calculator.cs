using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPFDivCalculator.Models
{
    internal class Calculator
    {
        public double Lhs { get; set; }

        public double Rhs { get; set; }

        public double Result { get; private set; }

        public void ExecuteDiv()
        {
            Result = Lhs / Rhs;
        }
    }
}
