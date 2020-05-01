using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Input;

namespace ModelEditor.Command
{
    class CommandObject : ICommand
    {
        public CommandObject(Action<object> execute, Func<object, bool> canExecute = null)
        {
            _execute = execute;
            _canExecute = canExecute;
        }

        /// <summary>
        /// 実行可能状態の変更通知
        /// </summary>
        protected void RaiseCanExecuteChanged()
        {
            RaiseCanExecuteChanged(EventArgs.Empty);
        }

        /// <summary>
        /// 実行可能状態の変更通知
        /// </summary>
        /// <param name="e">イベント引数</param>
        protected void RaiseCanExecuteChanged(EventArgs e)
        {
            var handler = CanExecuteChanged;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        private Action<object> _execute;
        private Func<object, bool> _canExecute;

        #region ICommandの実装
        public event EventHandler CanExecuteChanged;

        /// <summary>
        /// コマンド実行可能か
        /// </summary>
        /// <param name="parameter">パラメータ</param>
        /// <returns></returns>
        public bool CanExecute(object parameter)
        {
            if (_canExecute != null)
            {
                return _canExecute(parameter);
            }

            return true;
        }

        /// <summary>
        /// コマンド実行
        /// </summary>
        /// <param name="parameter">パラメータ</param>
        public void Execute(object parameter)
        {
            _execute?.Invoke(parameter);
        }
        #endregion ICommandの実装
    }
}
