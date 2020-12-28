export interface ITokens {
	refresh_token: string;
	access_token: string;
}

export interface IRefresh {
	refresh: string
}

export interface IAccess {
	access_token: string,
	response: string
}

export function ioIAccess(object: any): object is IAccess {
	return 'access' in object;
}
