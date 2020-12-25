import * as React from "react";
import {FC, useEffect, useState} from 'react';
import {useSelector} from 'react-redux';

import {SmallMoment} from 'components/SmallMoment';
import {IMoment} from 'types/moments';
import {ioIError} from 'types/common';
import {IUserStore} from 'types/user';
import {APIUser} from 'utils/api';

import './recomended-page.scss';

export const RecomendedPage: FC = () => {

	const [moments, setMoments] = useState<IMoment[]>(null);
  const userStore: IUserStore = useSelector(state => state.user);

	useEffect(() => {
		APIUser.getAllMoments()
			.then(res => {
				if (!ioIError(res)) {
					setMoments(res.data);
				}
			})
	}, []);

	return(
		<div className={'recomended-page'}>
			<div className={'content-wrapper F-R-SP'}>
				{moments?.map((moment, index) => (
					<div className={'moment-wrapper'} key={index} >
						<SmallMoment
							likesQuantity={Number(moment.amount_likes)}
							path={moment.attach}
							isLiked={(moment.liked_users.indexOf(`i${userStore.id}`) === -1 ? false : true)}
							id={Number(moment.post_id)}
						/>
					</div>
				))}
			</div>
		</div>
	);
}