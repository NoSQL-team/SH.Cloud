import * as React from "react";
import * as ReactDOM from "react-dom";
import {Provider} from 'react-redux';

import {App} from './App';
import {store} from './store/store'

window.onload = function() {
  ReactDOM.render(
    <Provider store={store} >
      <App />
    </Provider>,
    document.getElementById("wrapper")
  );
};