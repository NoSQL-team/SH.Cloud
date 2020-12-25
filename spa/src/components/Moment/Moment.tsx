import * as React from "react";
import {ReactElement, FC, useState, useEffect} from 'react';
import {Link} from 'react-router-dom';
import {isMobile} from 'react-device-detect';
import {useSelector} from 'react-redux'

import {MomentDto} from 'models/MomentDto';
import {APIUser} from 'utils/api';
import {ioIError} from 'types/common';
import {IUserProfile, IUserStore} from 'types/user';
import LikedIcon from 'assests/moment/icons/liked.svg';
import UnlikedIcon from 'assests/moment/icons/unliked.svg';
import {useLike} from 'hooks/useLike';

import './moment.scss'

interface MomentProps extends MomentDto {
  
}

export const Moment: FC<MomentProps> = ({
  author,
  imgs,
  isLiked,
  title,
  id,
  description
}: MomentProps): ReactElement => {

  const [userProfile, setUserProfile] = useState<IUserProfile>(null);
  const userStore: IUserStore = useSelector(state => state.user);
  const {isLikedState, toggleLike} = useLike({
    isLiked: isLiked,
    id: id
  });
  
  useEffect(() => {
    APIUser.getUserById(author)
      .then((res) => {
        if (!ioIError(res)) {
          setUserProfile(res);
        }
      });
  }, []);

  return(
    <div className={isMobile ? 'moment-mobile' : 'moment'} >
      <div className={'F-R-SP title'} >
        <Link to={`/profile/${author}`} >
          <div className={'F-R-S'} >
            <img src={userProfile?.photo} />
            <div className={'author'}>{userProfile?.nickname}</div>
          </div>
        </Link>
        <div className={'title-text'}>{title}</div>
      </div>
      <Link to={`/moment/${id}/`} >
        {imgs.length != 0 && <img src={imgs} width={600} /> }
      </Link>
      <div className={'description'}>
        {description}
      </div>
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
    </div>
  );
}