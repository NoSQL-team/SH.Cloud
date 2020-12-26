import * as React from "react";
import {FC} from 'react';
import {Link} from 'react-router-dom';

import ProfileIcon from 'assests/header/icons/profile.svg';
import CompassIcon from 'assests/header/icons/compass.svg';
import HomeIcon from 'assests/header/icons/home.svg';
import PlusIcon from 'assests/header/icons/plus.svg';
import FindIcon from 'assests/header/icons/find.svg';
import {HEADER_TITLE} from 'constants/header';

import './header.scss'

interface HeaderProps {
	toggleModal: () => void,
	closeWindow: () => void
}

export const Header: FC<HeaderProps> = ({
	toggleModal,
	closeWindow
}: HeaderProps) => {
	return(
		<>
			<div className={'Header'}>
				<div className={'header-container' + ' F-R-SP'}>
					<Link to={'/'} >
						<div className={'title-text'} onClick={closeWindow} >{HEADER_TITLE}</div>
					</Link>
					<div className={'icons F-R-SP'}>
						<div 
							onClick={toggleModal}
							className={'plus'}
						>
							<PlusIcon />
						</div>
						<Link to={'/'}>
							<div className={'home'} onClick={closeWindow} >
								<HomeIcon />
							</div>
						</Link>
						<Link to={'/find-friends'}>
							<div className={'home'} onClick={closeWindow} >
								<FindIcon />
							</div>
						</Link>
						<Link to={'/recomended'} >
							<div className={'compass'} onClick={closeWindow} >
								<CompassIcon />
							</div>
						</Link>
						<Link to={'/profile'} >
							<div className={'profile'} onClick={closeWindow} >
								<ProfileIcon />
							</div>
						</Link>
					</div>
				</div>
			</div>
		</>
	);
}
