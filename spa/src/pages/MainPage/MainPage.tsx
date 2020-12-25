import * as React from "react";
import {isMobile} from 'react-device-detect'
import {FC, useEffect, useState} from 'react';
import {useSelector} from 'react-redux';

import {Moment} from 'components/Moment';
import {IUserStore} from 'types/user';
import {IMoment} from 'types/moments';
import {APIUser} from 'utils/api';
import {ioIError} from "types/common";

import './main-page.scss';

export const MainPage: FC = () => {

	const userStore: IUserStore = useSelector(state => state.user);
	const [moments, setMoments] = useState<IMoment[]>(null);

	useEffect(() => {
		APIUser.getUserTape(userStore.id)
			.then(res => {
				if (!ioIError(res)) {
					setMoments(res.data);
				}
			})
	}, []);

	
	return(
		<div className={isMobile ? 'main-page-mobile' : 'main-page'}>
			<div className={'content-wrapper F-C-S'} >
				{moments?.map((moment: IMoment, index: number) => (
					<div className={'moment-wrapper'} key={index}>
						<Moment 
							author={Number(moment.creator_id)}
							title={moment.title}
							imgs={moment.attach}
							isLiked={(moment.liked_users.indexOf(`i${userStore.id}`) === -1 ? false : true)}
							id={Number(moment.post_id)}
							description={moment.text}
						/>
					</div>
				))}
			</div>
		</div>
	);
}
