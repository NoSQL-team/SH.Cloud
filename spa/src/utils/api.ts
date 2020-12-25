import {ITokens, IAccess} from 'types/tokens';
import {IUserAuthData, IUserProfile, IUserId} from 'types/user';
import {IGetData, IError, ISucces, IChangeUserForm, IRegForm, ioIError} from 'types/common';
import {IIsFriendStruct, IUserFriendsStat} from 'types/friends';
import {ICreateMoment} from 'types/moments';
import {IMoment} from 'types/moments';

const API = 'http://127.0.0.1:9999';

export class APIUser {
	static getToken = async (body: IUserAuthData):Promise<ITokens | IError> => {
		let response = await fetch(API + '/api/auth/auth/', {
			method: 'POST',
			body: JSON.stringify(body),
			mode: "cors"
		});
		let responseJSON: Promise<ITokens | IError> = response.json();
		return responseJSON;
	}
	static getAccessToken = async (token: string, userId: number):Promise<IAccess | IError> => {
		let response = await fetch(API + '/api/auth/refresh/', {
			method: 'POST',
			body: JSON.stringify({
				'refresh_token': token,
				'user_id': userId
			}),
			mode: "cors"
		});
		let responseJSON: Promise<IAccess | IError> = await response.json();
		return responseJSON;
	}
	static getMe = async (userId: number):Promise<IUserProfile | IError> => {
		let response = await fetch(API + `/api/users/${userId}/`, {
			method: 'GET',
			mode: 'cors'
		});
		let responseJSON: Promise<IUserProfile | IError> = response.json();
		return responseJSON;
	}
	static changeUserData = async (token: string, userForm: IChangeUserForm, userId: number):Promise<ISucces | IError> => {
		userForm['id'] = String(userId);
		let response = await APIUser.getAccessToken(token, userId)
			.then( async (accessToken) => {
				if (ioIError(accessToken)) {
					return {
						error: 'token_not_valid'
					}
				} else {
					let response = await fetch(API + '/api/users/update/', {
						method: 'POST',
						body: JSON.stringify(userForm)
					});
					return response.json();
				}
			});
		return response;
	}
	static regUser = async (userForm: IRegForm):Promise<ISucces | IError> => {
		userForm['photo'] = 'https://firebasestorage.googleapis.com/v0/b/noskool-sn.appspot.com/o/unnamed.jpg?alt=media&token=e3f065f3-a5f5-41f8-b717-a97d2fa5e207';
		delete userForm['repeat_password'];
		let response = await fetch(API + '/api/users/create/', {
			method: 'POST',
			body: JSON.stringify(userForm),
			mode: "cors"
		});
		let responseJSON: Promise<ISucces | IError> = response.json();
		return responseJSON;
	}
	static getUserById = async (userId: number):Promise<IUserProfile | IError> => {
		let response = await fetch(API + `/api/users/${userId}/`, {
			method: 'GET',
			mode: 'cors'
		});
		let responseJSON: Promise<IUserProfile | IError> = response.json();
		return responseJSON;
	}
	static getIsPurposeUserFriend = async (purposeId: number, userId: number):Promise<IIsFriendStruct | IError> => {
		let response = await fetch(API + '/api/friends/is_friend/', {
			method: 'POST',
			mode: 'cors',
			body: JSON.stringify({
				user_1: userId,
				user_2: purposeId
			})
		});
		let responseJSON: Promise<IIsFriendStruct | IError> = response.json();
		return responseJSON;
	}
	static getUserId = async (username: string):Promise<IUserId | IError> => {
		let response = await fetch(API + `/api/users/${username}/`);
		let responseJSON: Promise<IUserId | IError> = response.json();
		return responseJSON;
	}
	static changeFriends = async (token: string, type: 'add' | 'del', userId: number, purposeId: number):Promise<ISucces | IError> => {
		let response = await APIUser.getAccessToken(token, userId)
			.then( async (accessToken) => {
				if (ioIError(accessToken)) {
					return {
						error: 'token_not_valid'
					}
				} else {
					let response = await fetch(API + (type === 'add' ? '/api/friends/add/' : '/api/friends/delete/'), {
						method: 'POST',
						mode: 'cors',
						body: JSON.stringify({
							user_1: userId,
							user_2: purposeId
						})
					});
					return response.json();
				}
			});
		return response;
	}
	static getUserFriendStat = async (userId: number):Promise<IUserFriendsStat | IError> => {
		let response = await fetch(API + `/api/friends/get_stat/`, {
			method: 'POST',
			body: JSON.stringify({
				"user_1": userId
			}),
			mode: "cors"
		});
		let responseJSON: Promise<IUserFriendsStat | IError> = response.json();
		return responseJSON;
	}
	static createMoment = async (token: string, momentForm: ICreateMoment):Promise<ISucces | IError> => {
		let response = await fetch(API + '/api/posts/create/', {
			method: 'POST',
			mode: 'cors',
			body: JSON.stringify(momentForm)
		});
		let responseJSON: Promise<ISucces | IError> = response.json();
		return responseJSON;
	}
	static getUserTape = async (userId: number):Promise<IGetData<IMoment[]> | IError> => {
		let response = await fetch(API + `/api/posts/fuser/?user_id=${userId}`, {
			method: 'GET',
			mode: 'cors'
		});
		let responseJSON: Promise<IGetData<IMoment[]> | IError> = response.json();
		return responseJSON;
	}
	static addLike = async (token: string, user: number, moment: number):Promise<ISucces | IError> => {
		let response = await APIUser.getAccessToken(token, user)
			.then( async (accessToken) => {
				if (ioIError(accessToken)) {
					return {
						error: 'token_not_valid'
					}
				} else {
					let response = await fetch(API + `/api/posts/like/add/?post_id=${moment}&user_id=${user}`, {
						method: 'POST',
						mode: 'cors'
					});
					return response.json();
				}
			});
		return response;
	}
	static delLike = async (token: string, user: number, moment: number):Promise<ISucces | IError> => {
		let response = await APIUser.getAccessToken(token, user)
			.then( async (accessToken) => {
				if (ioIError(accessToken)) {
					return {
						error: 'token_not_valid'
					}
				} else {
					let response = await fetch(API + `/api/posts/like/del/?post_id=${moment}&user_id=${user}`, {
						method: 'POST',
						mode: 'cors'
					});
					return response.json();
				}
			});
		return response;
	}
	static getMomentByIdUserid = async (momentId: number):Promise<IMoment | IError> => {
		let response = await fetch(API + `/api/posts/post/?post_id=${momentId}`, {
			method: 'GET',
			mode: 'cors'
		});
		let responseJSON: Promise<IMoment | IError> = response.json();
		return responseJSON;
	}
	static getAllMoments = async ():Promise<IGetData<IMoment[]> | IError> => {
		let response = await fetch(API + `/api/posts/all/`, {
			method: 'GET',
			mode: 'cors'
		});
		let responseJSON: Promise<IGetData<IMoment[]> | IError> = response.json();
		return responseJSON;
	}
	static getUser = async (userId: number):Promise<IGetData<IMoment[]> | IError> => {
		let response = await fetch(API + `/api/posts/user/?user_id=${userId}`, {
			method: 'GET',
			mode: 'cors'
		});
		let responseJSON: Promise<IGetData<IMoment[]> | IError> = response.json();
		return responseJSON;
	}
}
