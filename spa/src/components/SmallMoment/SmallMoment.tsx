import * as React from "react";
import {ReactElement, useState, FC} from 'react';
import {useSelector} from 'react-redux';
import {Link} from 'react-router-dom';

import {SmallMomentDto} from 'models/SmallMomentDto'
import {isMobile} from 'react-device-detect'
import LikedIcon from 'assests/moment/icons/liked.svg';
import UnlikedIcon from 'assests/moment/icons/unliked.svg';
import {IUserStore} from 'types/user';

import './small-moment.scss'

interface SmallMomentProps extends SmallMomentDto {

}

export const SmallMoment: FC<SmallMomentProps> = ({
  path,
  likesQuantity,
  isLiked,
  id
}: SmallMomentProps): ReactElement => {

  const [isHover, setIsHover] = useState<boolean>(false);
  const userStore: IUserStore = useSelector(state => state.user);

  return(
    <div className={isMobile ? 'small-moment-mobile' : 'small-moment'} >
      <img 
        src={path} 
        className={'image'} 
        onMouseEnter={() => { setIsHover(true); }} 
        />
      {!isMobile && isHover &&
        <Link to={`/moment/${id}/`} >
          <div 
            className={'hover-block F-C-C'} 
            onMouseLeave={() => { setIsHover(false); }}
            >
            <div className={'icons F-R-SP'} >
              <div className={'like F-R-SP'} >
                {isLiked ? (
                  <LikedIcon />
                ) : (
                  <UnlikedIcon />
                )}
                {likesQuantity}
              </div>
            </div>
          </div>
        </Link>
      }
    </div>
  );
}