using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using WPFDivCalculator.Models;

namespace WPFDivCalculator.ViewModels
{
    internal class MainViewModel : NotificationObject
    {
        public MainViewModel()
        {
            _calc = new Calculator();
        }

        private string _lhs;
        public string Lhs
        {
            get { return _lhs; }
            set 
            { 
                if (SetProperty(ref _lhs, value))
                {
                    DivCommand.RaiseCanExecuteChanged();
                }
            }
        }

        private string _rhs;
        public string Rhs
        {
            get { return _rhs; }
            set 
            { 
                if (SetProperty(ref _rhs, value))
                {
                    DivCommand.RaiseCanExecuteChanged();
                }
            }
        }

        private string _result;
        public string Result
        {
            get { return _result; }
            private set { SetProperty(ref _result, value); }
        }

        private DelegateCommand _divCommand;
        public DelegateCommand DivCommand
        {
            get
            {
                return _divCommand ?? (_divCommand = new DelegateCommand(
                    _ => { OnDivision(); },
                    _ =>
                    {
                        var dummy = 0.0;
                        if (!double.TryParse(Lhs, out dummy))
                        {
                            return false;
                        }
                        if (!double.TryParse(Rhs, out dummy))
                        {
                            return false;
                        }
                        return true;
                    }));
            }
        }

        private void OnDivision()
        {
            _calc.Lhs = double.Parse(Lhs);
            _calc.Rhs = double.Parse(Rhs);
            _calc.ExecuteDiv();
            Result = _calc.Result.ToString();
        }

        private Calculator _calc;
    }
}
