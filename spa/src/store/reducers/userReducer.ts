import {IAction} from 'types/common';
import { IUserStore } from 'types/user';
import {SET_AUTHS, NONE_AUTH} from 'store/actions/userAction';

const initialState: IUserStore = {
  login: '',
  refreshToken: '',
  id: 0
}

export const userReducer = (state: IUserStore = initialState, action: IAction<IUserStore>): IUserStore => {
  switch (action.type) {
    case SET_AUTHS:
      return {
        ...state,
        ...action.payload
      }
    case NONE_AUTH:
      return {
        ...state,
        ...action.payload
      }
    default:
      return state;
  }
}
