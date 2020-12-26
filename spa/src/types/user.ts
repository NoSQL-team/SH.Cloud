export interface IUserAuthData {
	username: string,
	password: string
}

export function ioIUserAuthData(object: any): object is IUserAuthData {
	return 'username' in object;
}

export interface IUserStore {
	login: string,
	refreshToken: string,
	id: number
}

export interface IUserProfile {
	firstname: string;
	lastname: string;
	nickname: string;
	email: string;
	photo: string;
}

export interface IUserId {
	id: string
}

export interface IFindUser {
	id: number;
	nickname: string;
	photo: string;
}
