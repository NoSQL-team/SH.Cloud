export interface ICreateMoment {
  user_id: number;
  title: string;
  text: string,
  attach: string;
}

export interface IMoment {
  post_id: string,
  creator_id: string,
  creation_date: string,
  title: string,
  text: string,
  attach: string,
  amount_likes: string,
  liked_users: string
}
