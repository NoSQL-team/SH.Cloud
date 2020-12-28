import * as React from "react";
import {FC, useEffect, useState} from 'react';
import {useSelector} from 'react-redux';
import {Link} from 'react-router-dom';

import {APIUser} from 'utils/api';
import {IMoment} from 'types/moments';
import {ioIError} from 'types/common';
import {IUserProfile, IUserStore} from 'types/user';
import {useLike} from 'hooks/useLike';
import LikedIcon from 'assests/moment/icons/liked.svg';
import UnlikedIcon from 'assests/moment/icons/unliked.svg';

import './moment-page.scss';

interface IMomentPageProps {
  match?: any
}

export const MomentPage: FC<IMomentPageProps> = ({
  match
}: IMomentPageProps) => {

	const [moment, setMoment] = useState<IMoment>(null);
  	const userStore: IUserStore = useSelector(state => state.user);
  	const [userProfile, setUserProfile] = useState<IUserProfile>(null);
	const {isLikedState, toggleLike, setRealLike} = useLike({
    isLiked: (moment?.liked_users.indexOf(`i${userStore.id}`) === -1 ? false : true),
    id: match?.params.id
  });

	useEffect(() => {
		APIUser.getMomentByIdUserid(match?.params.id)
			.then(res => {
				if (!ioIError(res)) {
					setMoment(res);
					setRealLike((res?.liked_users.indexOf(`i${userStore.id}`) === -1 ? false : true));
					APIUser.getUserById(Number(res.creator_id))
						.then((res) => {
							if (!ioIError(res)) {
								setUserProfile(res);
							}
						});
				}
			})
	}, [])

	return(
		<div className={'moment-page'}>
			<div className={'content-wrapper'} >
				<div className={'content-wrapper-card F-R-SP'}> 
					<img src={moment?.attach} className={'photo'} />
					<div className={'information F-C-S'}>
						<div className={'F-R-SP title'}>
							<div className={'icons'} >
								{isLikedState ? (
									<div className={'icon'} onClick={toggleLike} >
										<LikedIcon />
									</div> 
								) : (
									<div className={'icon'} onClick={toggleLike} >
										<UnlikedIcon />
									</div> 
								)}
							</div>
							{userStore.id === Number(moment?.creator_id) ? (
								<Link to={'/profile'} >
									<div className={'F-R-S'} >
										<img src={userProfile?.photo} />
										<div className={'author'}>{userProfile?.nickname}</div>
									</div>
								</Link>
							) : (
								<Link to={`/profile/${moment?.creator_id}`} >
									<div className={'F-R-S'} >
										<img src={userProfile?.photo} />
										<div className={'author'}>{userProfile?.nickname}</div>
									</div>
								</Link>
							)}
						</div>
						<div>
							<hr/>
						</div>
						<div className={'description'}>
							{moment?.text}
						</div>
					</div>
				</div>
			</div>
		</div>
	);
}
