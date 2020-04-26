using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Input;

namespace WPFItemsConrol
{
    class DelegateCommand : ICommand
    {
        private Action<object> _execute;

        private Func<object, bool> _canExecute;

        public DelegateCommand(Action<object> execute)
            : this(execute, null)
        {

        }

        public DelegateCommand(Action<object> execute, Func<object, bool> canExecute)
        {
            _execute = execute;
            _canExecute = canExecute;
        }

        #region ICommand
        public event EventHandler CanExecuteChanged;

        /// <summary>
        /// コマンド実行可能か
        /// </summary>
        public bool CanExecute(object parameter)
        {
            return _canExecute != null ? _canExecute(parameter) : true;
        }

        /// <summary>
        /// コマンド実行可能状態の変更
        /// </summary>
        public void RaiseCanExecuteChanged()
        {
            var handler = CanExecuteChanged;
            if (handler != null)
            {
                handler(this, EventArgs.Empty);
            }
        }

        /// <summary>
        /// コマンド実行
        /// </summary>
        public void Execute(object parameter)
        {
            if (_execute != null)
            {
                _execute(parameter);
            }
        }
        #endregion
    }
}
