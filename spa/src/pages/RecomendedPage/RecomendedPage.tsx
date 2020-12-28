import * as React from "react";
import {FC, useEffect, useState} from 'react';
import {useSelector} from 'react-redux';

import {IMoment} from 'types/moments';
import {ioIError} from 'types/common';
import {IUserStore} from 'types/user';
import {APIUser} from 'utils/api';
import {Gallery} from 'components/Gallery';

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
        <Gallery moments={moments} />
			</div>
		</div>
	);
}