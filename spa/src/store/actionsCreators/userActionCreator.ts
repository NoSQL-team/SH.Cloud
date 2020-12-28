import {IUserStore} from 'types/user';
import {IAction} from 'types/common';
import {SET_AUTHS} from 'store/actions/userAction';

export const setUserAuths = (payload: IUserStore):IAction<IUserStore> => ({
  type: SET_AUTHS,
  payload: payload
});

export const setNoneAuth = ():IAction<IUserStore> => ({
  type: SET_AUTHS,
  payload: {
    login: '',
    refreshToken: '',
    id: -1
  }
});
