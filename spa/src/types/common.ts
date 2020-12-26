import {IUserProfile} from './user';

export interface IAction<T> {
  type: string;
  payload: T;
}
export interface IGetDataArray<T> {
  data: T[];
}

export interface IGetData<T> {
  data: T;
}

export interface IError {
  error: string;
}

export interface ISucces {
  success: string;
}

export interface IChangeUserForm {
  nickname?: string;
  firstname?: string;
  lastname?: string;
  photo?: string;
  status?: string;
  ico_status?: string;
  id: string;
}

export interface IRegForm {
  nickname?: string;
  password?: string;
  repeat_password?: string;
  firstname?: string;
  lastname?: string;
  email?: string;
  photo?: string;
}

export function ioIRegForm(object: any): object is IRegForm {
	return 'nickname' in object;
}

export function ioIError(object: any): object is IError {
	return 'error' in object;
}

export function ioISuccesMessage(object: any): object is ISucces {
  return 'success' in object;
}
